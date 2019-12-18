#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ imgchunk_t ;
typedef  int /*<<< orphan*/  fchunk ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void free_chunks(imgchunk_t *fchunk, unsigned int *nfchunks)
{
	int i;
	for (i = 0; i < *nfchunks; i++) {
		if (fchunk[i].data != NULL) {
			kfree(fchunk[i].data);
		}
	}
	*nfchunks = 0;
	memset(fchunk, 0, sizeof(fchunk));

}