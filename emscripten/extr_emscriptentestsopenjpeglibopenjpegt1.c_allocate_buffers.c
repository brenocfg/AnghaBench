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
struct TYPE_3__ {int datasize; int* data; int flags_stride; int flagssize; int* flags; int w; int h; } ;
typedef  TYPE_1__ opj_t1_t ;
typedef  int flag_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opj_aligned_free (int*) ; 
 scalar_t__ opj_aligned_malloc (int) ; 

__attribute__((used)) static bool allocate_buffers(
		opj_t1_t *t1,
		int w,
		int h)
{
	int datasize=w * h;
	int flagssize;

	if(datasize > t1->datasize){
		opj_aligned_free(t1->data);
		t1->data = (int*) opj_aligned_malloc(datasize * sizeof(int));
		if(!t1->data){
			return false;
		}
		t1->datasize=datasize;
	}
	memset(t1->data,0,datasize * sizeof(int));

	t1->flags_stride=w+2;
	flagssize=t1->flags_stride * (h+2);

	if(flagssize > t1->flagssize){
		opj_aligned_free(t1->flags);
		t1->flags = (flag_t*) opj_aligned_malloc(flagssize * sizeof(flag_t));
		if(!t1->flags){
			return false;
		}
		t1->flagssize=flagssize;
	}
	memset(t1->flags,0,flagssize * sizeof(flag_t));

	t1->w=w;
	t1->h=h;

	return true;
}