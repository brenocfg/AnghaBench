#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct bstring {struct bstring* next; int /*<<< orphan*/  length; TYPE_1__ d; } ;
struct bcache {int num_buckets; int structure_size; struct bstring** bucket; scalar_t__ unique_count; int /*<<< orphan*/  expand_hash_count; int /*<<< orphan*/  expand_count; } ;
typedef  int /*<<< orphan*/  sizes ;
typedef  int /*<<< orphan*/  new_buckets ;

/* Variables and functions */
 unsigned int hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bstring**,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  xfree (struct bstring**) ; 
 scalar_t__ xmalloc (size_t) ; 

__attribute__((used)) static void
expand_hash_table (struct bcache *bcache)
{
  /* A table of good hash table sizes.  Whenever we grow, we pick the
     next larger size from this table.  sizes[i] is close to 1 << (i+10),
     so we roughly double the table size each time.  After we fall off 
     the end of this table, we just double.  Don't laugh --- there have
     been executables sighted with a gigabyte of debug info.  */
  static unsigned long sizes[] = { 
    1021, 2053, 4099, 8191, 16381, 32771,
    65537, 131071, 262144, 524287, 1048573, 2097143,
    4194301, 8388617, 16777213, 33554467, 67108859, 134217757,
    268435459, 536870923, 1073741827, 2147483659UL
  };
  unsigned int new_num_buckets;
  struct bstring **new_buckets;
  unsigned int i;

  /* Count the stats.  Every unique item needs to be re-hashed and
     re-entered.  */
  bcache->expand_count++;
  bcache->expand_hash_count += bcache->unique_count;

  /* Find the next size.  */
  new_num_buckets = bcache->num_buckets * 2;
  for (i = 0; i < (sizeof (sizes) / sizeof (sizes[0])); i++)
    if (sizes[i] > bcache->num_buckets)
      {
	new_num_buckets = sizes[i];
	break;
      }

  /* Allocate the new table.  */
  {
    size_t new_size = new_num_buckets * sizeof (new_buckets[0]);
    new_buckets = (struct bstring **) xmalloc (new_size);
    memset (new_buckets, 0, new_size);

    bcache->structure_size -= (bcache->num_buckets
			       * sizeof (bcache->bucket[0]));
    bcache->structure_size += new_size;
  }

  /* Rehash all existing strings.  */
  for (i = 0; i < bcache->num_buckets; i++)
    {
      struct bstring *s, *next;

      for (s = bcache->bucket[i]; s; s = next)
	{
	  struct bstring **new_bucket;
	  next = s->next;

	  new_bucket = &new_buckets[(hash (&s->d.data, s->length)
				     % new_num_buckets)];
	  s->next = *new_bucket;
	  *new_bucket = s;
	}
    }

  /* Plug in the new table.  */
  if (bcache->bucket)
    xfree (bcache->bucket);
  bcache->bucket = new_buckets;
  bcache->num_buckets = new_num_buckets;
}