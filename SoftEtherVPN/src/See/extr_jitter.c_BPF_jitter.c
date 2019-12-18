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
struct bpf_insn {int dummy; } ;
struct JIT_BPF_Filter {struct JIT_BPF_Filter* mem; int /*<<< orphan*/ * Function; } ;
typedef  struct JIT_BPF_Filter JIT_BPF_Filter ;
typedef  struct JIT_BPF_Filter INT ;

/* Variables and functions */
 int BPF_MEMWORDS ; 
 int /*<<< orphan*/ * BPFtoX86 (struct bpf_insn*,struct JIT_BPF_Filter,struct JIT_BPF_Filter*) ; 
 scalar_t__ ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,char) ; 
 int /*<<< orphan*/  ExFreePool (struct JIT_BPF_Filter*) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  free (struct JIT_BPF_Filter*) ; 
 scalar_t__ malloc (int) ; 

JIT_BPF_Filter* BPF_jitter(struct bpf_insn *fp, INT nins)
{
	JIT_BPF_Filter *Filter;


	// Allocate the filter structure
#ifdef NTKERNEL
	Filter=(struct JIT_BPF_Filter*)ExAllocatePoolWithTag(NonPagedPool, sizeof(struct JIT_BPF_Filter), '2JWA');
#else
	Filter=(struct JIT_BPF_Filter*)malloc(sizeof(struct JIT_BPF_Filter));
#endif
	if(Filter==NULL)
	{
		return NULL;
	}

	// Allocate the filter's memory
#ifdef NTKERNEL
	Filter->mem=(INT*)ExAllocatePoolWithTag(NonPagedPool, BPF_MEMWORDS*sizeof(INT), '3JWA');
#else
	Filter->mem=(INT*)malloc(BPF_MEMWORDS*sizeof(INT));
#endif
	if(Filter->mem==NULL)
	{
#ifdef NTKERNEL
		ExFreePool(Filter);
#else
		free(Filter);
#endif
		return NULL;
	}

	// Create the binary
	if((Filter->Function = BPFtoX86(fp, nins, Filter->mem))==NULL)
	{
#ifdef NTKERNEL
		ExFreePool(Filter->mem);
		ExFreePool(Filter);
#else
		free(Filter->mem);
		free(Filter);
#endif
		return NULL;
	}

	return Filter;

}