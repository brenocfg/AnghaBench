#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct objalloc_chunk {char* current_ptr; struct objalloc_chunk* next; } ;
struct objalloc {char* current_ptr; int current_space; void* chunks; } ;
typedef  void* PTR ;

/* Variables and functions */
 int CHUNK_HEADER_SIZE ; 
 int CHUNK_SIZE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  free (struct objalloc_chunk*) ; 

void
objalloc_free_block (struct objalloc *o, PTR block)
{
  struct objalloc_chunk *p, *small;
  char *b = (char *) block;

  /* First set P to the chunk which contains the block we are freeing,
     and set Q to the last small object chunk we see before P.  */
  small = NULL;
  for (p = (struct objalloc_chunk *) o->chunks; p != NULL; p = p->next)
    {
      if (p->current_ptr == NULL)
	{
	  if (b > (char *) p && b < (char *) p + CHUNK_SIZE)
	    break;
	  small = p;
	}
      else
	{
	  if (b == (char *) p + CHUNK_HEADER_SIZE)
	    break;
	}
    }

  /* If we can't find the chunk, the caller has made a mistake.  */
  if (p == NULL)
    abort ();

  if (p->current_ptr == NULL)
    {
      struct objalloc_chunk *q;
      struct objalloc_chunk *first;

      /* The block is in a chunk containing small objects.  We can
	 free every chunk through SMALL, because they have certainly
	 been allocated more recently.  After SMALL, we will not see
	 any chunks containing small objects; we can free any big
	 chunk if the current_ptr is greater than or equal to B.  We
	 can then reset the new current_ptr to B.  */

      first = NULL;
      q = (struct objalloc_chunk *) o->chunks;
      while (q != p)
	{
	  struct objalloc_chunk *next;

	  next = q->next;
	  if (small != NULL)
	    {
	      if (small == q)
		small = NULL;
	      free (q);
	    }
	  else if (q->current_ptr > b)
	    free (q);
	  else if (first == NULL)
	    first = q;

	  q = next;
	}

      if (first == NULL)
	first = p;
      o->chunks = (PTR) first;

      /* Now start allocating from this small block again.  */
      o->current_ptr = b;
      o->current_space = ((char *) p + CHUNK_SIZE) - b;
    }
  else
    {
      struct objalloc_chunk *q;
      char *current_ptr;

      /* This block is in a large chunk by itself.  We can free
         everything on the list up to and including this block.  We
         then start allocating from the next chunk containing small
         objects, setting current_ptr from the value stored with the
         large chunk we are freeing.  */

      current_ptr = p->current_ptr;
      p = p->next;

      q = (struct objalloc_chunk *) o->chunks;
      while (q != p)
	{
	  struct objalloc_chunk *next;

	  next = q->next;
	  free (q);
	  q = next;
	}

      o->chunks = (PTR) p;

      while (p->current_ptr != NULL)
	p = p->next;

      o->current_ptr = current_ptr;
      o->current_space = ((char *) p + CHUNK_SIZE) - current_ptr;
    }
}