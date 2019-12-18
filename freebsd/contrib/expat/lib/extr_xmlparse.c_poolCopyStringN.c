#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XML_Char ;
struct TYPE_6__ {int /*<<< orphan*/ * start; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ STRING_POOL ;

/* Variables and functions */
 int /*<<< orphan*/  poolAppendChar (TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  poolFinish (TYPE_1__*) ; 
 int /*<<< orphan*/  poolGrow (TYPE_1__*) ; 

__attribute__((used)) static const XML_Char *
poolCopyStringN(STRING_POOL *pool, const XML_Char *s, int n)
{
  if (!pool->ptr && !poolGrow(pool)) {
    /* The following line is unreachable given the current usage of
     * poolCopyStringN().  Currently it is called from exactly one
     * place to copy the text of a simple general entity.  By that
     * point, the name of the entity is already stored in the pool, so
     * pool->ptr cannot be NULL.
     *
     * If poolCopyStringN() is used elsewhere as it well might be,
     * this line may well become executable again.  Regardless, this
     * sort of check shouldn't be removed lightly, so we just exclude
     * it from the coverage statistics.
     */
    return NULL; /* LCOV_EXCL_LINE */
  }
  for (; n > 0; --n, s++) {
    if (!poolAppendChar(pool, *s))
      return NULL;
  }
  s = pool->start;
  poolFinish(pool);
  return s;
}