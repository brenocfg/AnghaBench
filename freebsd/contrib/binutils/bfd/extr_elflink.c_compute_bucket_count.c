#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct elf_backend_data {TYPE_1__* s; } ;
struct bfd_link_info {scalar_t__ optimize; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {size_t dynsymcount; int /*<<< orphan*/ * dynobj; } ;
struct TYPE_3__ {int sizeof_hash_entry; } ;
typedef  unsigned long BFD_HOST_U_64_BIT ;

/* Variables and functions */
 unsigned long BFD_TARGET_PAGESIZE ; 
 unsigned long* bfd_malloc (int) ; 
 unsigned long* elf_buckets ; 
 TYPE_2__* elf_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  free (unsigned long*) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (unsigned long*,char,unsigned long) ; 

__attribute__((used)) static size_t
compute_bucket_count (struct bfd_link_info *info, unsigned long int *hashcodes,
		      unsigned long int nsyms, int gnu_hash)
{
  size_t dynsymcount = elf_hash_table (info)->dynsymcount;
  size_t best_size = 0;
  unsigned long int i;
  bfd_size_type amt;

  /* We have a problem here.  The following code to optimize the table
     size requires an integer type with more the 32 bits.  If
     BFD_HOST_U_64_BIT is set we know about such a type.  */
#ifdef BFD_HOST_U_64_BIT
  if (info->optimize)
    {
      size_t minsize;
      size_t maxsize;
      BFD_HOST_U_64_BIT best_chlen = ~((BFD_HOST_U_64_BIT) 0);
      bfd *dynobj = elf_hash_table (info)->dynobj;
      const struct elf_backend_data *bed = get_elf_backend_data (dynobj);
      unsigned long int *counts;

      /* Possible optimization parameters: if we have NSYMS symbols we say
	 that the hashing table must at least have NSYMS/4 and at most
	 2*NSYMS buckets.  */
      minsize = nsyms / 4;
      if (minsize == 0)
	minsize = 1;
      best_size = maxsize = nsyms * 2;
      if (gnu_hash)
	{
	  if (minsize < 2)
	    minsize = 2;
	  if ((best_size & 31) == 0)
	    ++best_size;
	}

      /* Create array where we count the collisions in.  We must use bfd_malloc
	 since the size could be large.  */
      amt = maxsize;
      amt *= sizeof (unsigned long int);
      counts = bfd_malloc (amt);
      if (counts == NULL)
	return 0;

      /* Compute the "optimal" size for the hash table.  The criteria is a
	 minimal chain length.  The minor criteria is (of course) the size
	 of the table.  */
      for (i = minsize; i < maxsize; ++i)
	{
	  /* Walk through the array of hashcodes and count the collisions.  */
	  BFD_HOST_U_64_BIT max;
	  unsigned long int j;
	  unsigned long int fact;

	  if (gnu_hash && (i & 31) == 0)
	    continue;

	  memset (counts, '\0', i * sizeof (unsigned long int));

	  /* Determine how often each hash bucket is used.  */
	  for (j = 0; j < nsyms; ++j)
	    ++counts[hashcodes[j] % i];

	  /* For the weight function we need some information about the
	     pagesize on the target.  This is information need not be 100%
	     accurate.  Since this information is not available (so far) we
	     define it here to a reasonable default value.  If it is crucial
	     to have a better value some day simply define this value.  */
# ifndef BFD_TARGET_PAGESIZE
#  define BFD_TARGET_PAGESIZE	(4096)
# endif

	  /* We in any case need 2 + DYNSYMCOUNT entries for the size values
	     and the chains.  */
	  max = (2 + dynsymcount) * bed->s->sizeof_hash_entry;

# if 1
	  /* Variant 1: optimize for short chains.  We add the squares
	     of all the chain lengths (which favors many small chain
	     over a few long chains).  */
	  for (j = 0; j < i; ++j)
	    max += counts[j] * counts[j];

	  /* This adds penalties for the overall size of the table.  */
	  fact = i / (BFD_TARGET_PAGESIZE / bed->s->sizeof_hash_entry) + 1;
	  max *= fact * fact;
# else
	  /* Variant 2: Optimize a lot more for small table.  Here we
	     also add squares of the size but we also add penalties for
	     empty slots (the +1 term).  */
	  for (j = 0; j < i; ++j)
	    max += (1 + counts[j]) * (1 + counts[j]);

	  /* The overall size of the table is considered, but not as
	     strong as in variant 1, where it is squared.  */
	  fact = i / (BFD_TARGET_PAGESIZE / bed->s->sizeof_hash_entry) + 1;
	  max *= fact;
# endif

	  /* Compare with current best results.  */
	  if (max < best_chlen)
	    {
	      best_chlen = max;
	      best_size = i;
	    }
	}

      free (counts);
    }
  else
#endif /* defined (BFD_HOST_U_64_BIT) */
    {
      /* This is the fallback solution if no 64bit type is available or if we
	 are not supposed to spend much time on optimizations.  We select the
	 bucket count using a fixed set of numbers.  */
      for (i = 0; elf_buckets[i] != 0; i++)
	{
	  best_size = elf_buckets[i];
	  if (nsyms < elf_buckets[i + 1])
	    break;
	}
      if (gnu_hash && best_size < 2)
	best_size = 2;
    }

  return best_size;
}