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
struct object {int dummy; } ;
struct fde_vector {size_t count; int /*<<< orphan*/  const** array; } ;
typedef  scalar_t__ (* fde_compare_t ) (struct object*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ;
typedef  int /*<<< orphan*/  const fde ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static inline void
fde_split (struct object *ob, fde_compare_t fde_compare,
	   struct fde_vector *linear, struct fde_vector *erratic)
{
  static const fde *marker;
  size_t count = linear->count;
  const fde **chain_end = &marker;
  size_t i, j, k;

  /* This should optimize out, but it is wise to make sure this assumption
     is correct. Should these have different sizes, we cannot cast between
     them and the overlaying onto ERRATIC will not work.  */
  gcc_assert (sizeof (const fde *) == sizeof (const fde **));

  for (i = 0; i < count; i++)
    {
      const fde **probe;

      for (probe = chain_end;
	   probe != &marker && fde_compare (ob, linear->array[i], *probe) < 0;
	   probe = chain_end)
	{
	  chain_end = (const fde **) erratic->array[probe - linear->array];
	  erratic->array[probe - linear->array] = NULL;
	}
      erratic->array[i] = (const fde *) chain_end;
      chain_end = &linear->array[i];
    }

  /* Each entry in LINEAR which is part of the linear sequence we have
     discovered will correspond to a non-NULL entry in the chain we built in
     the ERRATIC array.  */
  for (i = j = k = 0; i < count; i++)
    if (erratic->array[i])
      linear->array[j++] = linear->array[i];
    else
      erratic->array[k++] = linear->array[i];
  linear->count = j;
  erratic->count = k;
}