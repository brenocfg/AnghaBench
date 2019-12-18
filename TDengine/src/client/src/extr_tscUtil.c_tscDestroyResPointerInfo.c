#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int numOfnchar; int /*<<< orphan*/ * bytes; int /*<<< orphan*/ ** buffer; int /*<<< orphan*/ * tsrow; } ;
typedef  TYPE_1__ SSqlRes ;

/* Variables and functions */
 int /*<<< orphan*/  tfree (int /*<<< orphan*/ *) ; 

void tscDestroyResPointerInfo(SSqlRes* pRes) {
  // free all buffers containing the multibyte string
  for (int i = 0; i < pRes->numOfnchar; i++) {
    if (pRes->buffer[i] != NULL) {
      tfree(pRes->buffer[i]);
    }
  }

  tfree(pRes->tsrow);

  pRes->numOfnchar = 0;
  pRes->buffer = NULL;
  pRes->bytes = NULL;
}