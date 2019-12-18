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
struct objalloc {unsigned long current_space; char* current_ptr; int /*<<< orphan*/ * chunks; } ;
typedef  int /*<<< orphan*/ * PTR ;

/* Variables and functions */
 unsigned long BIG_REQUEST ; 
 unsigned long CHUNK_HEADER_SIZE ; 
 unsigned long CHUNK_SIZE ; 
 unsigned long OBJALLOC_ALIGN ; 
 scalar_t__ malloc (unsigned long) ; 
 int /*<<< orphan*/ * objalloc_alloc (struct objalloc*,unsigned long) ; 

PTR
_objalloc_alloc (struct objalloc *o, unsigned long original_len)
{
  unsigned long len = original_len;

  /* We avoid confusion from zero sized objects by always allocating
     at least 1 byte.  */
  if (len == 0)
    len = 1;

  len = (len + OBJALLOC_ALIGN - 1) &~ (OBJALLOC_ALIGN - 1);

  /* CVE-2012-3509: Check for overflow in the alignment operation above
   * and then malloc argument below. */
  if (len + CHUNK_HEADER_SIZE < original_len)
      return NULL;

  if (len <= o->current_space)
    {
      o->current_ptr += len;
      o->current_space -= len;
      return (PTR) (o->current_ptr - len);
    }

  if (len >= BIG_REQUEST)
    {
      char *ret;
      struct objalloc_chunk *chunk;

      ret = (char *) malloc (CHUNK_HEADER_SIZE + len);
      if (ret == NULL)
	return NULL;

      chunk = (struct objalloc_chunk *) ret;
      chunk->next = (struct objalloc_chunk *) o->chunks;
      chunk->current_ptr = o->current_ptr;

      o->chunks = (PTR) chunk;

      return (PTR) (ret + CHUNK_HEADER_SIZE);
    }
  else
    {
      struct objalloc_chunk *chunk;

      chunk = (struct objalloc_chunk *) malloc (CHUNK_SIZE);
      if (chunk == NULL)
	return NULL;
      chunk->next = (struct objalloc_chunk *) o->chunks;
      chunk->current_ptr = NULL;

      o->current_ptr = (char *) chunk + CHUNK_HEADER_SIZE;
      o->current_space = CHUNK_SIZE - CHUNK_HEADER_SIZE;

      o->chunks = (PTR) chunk;

      return objalloc_alloc (o, len);
    }
}