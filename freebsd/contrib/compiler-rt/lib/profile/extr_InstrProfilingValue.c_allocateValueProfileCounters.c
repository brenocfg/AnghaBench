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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  Values; scalar_t__* NumValueSites; } ;
typedef  TYPE_1__ __llvm_profile_data ;
typedef  int /*<<< orphan*/  ValueProfNode ;

/* Variables and functions */
 int /*<<< orphan*/  COMPILER_RT_BOOL_CMPXCHG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  INSTR_PROF_MAX_NUM_VAL_PER_SITE ; 
 size_t IPVK_First ; 
 size_t IPVK_Last ; 
 int /*<<< orphan*/  VPMaxNumValsPerSite ; 
 scalar_t__ calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hasNonDefaultValsPerSite ; 
 scalar_t__ hasStaticCounters ; 

__attribute__((used)) static int allocateValueProfileCounters(__llvm_profile_data *Data) {
  uint64_t NumVSites = 0;
  uint32_t VKI;

  /* This function will never be called when value site array is allocated
     statically at compile time.  */
  hasStaticCounters = 0;
  /* When dynamic allocation is enabled, allow tracking the max number of
   * values allowd.  */
  if (!hasNonDefaultValsPerSite)
    VPMaxNumValsPerSite = INSTR_PROF_MAX_NUM_VAL_PER_SITE;

  for (VKI = IPVK_First; VKI <= IPVK_Last; ++VKI)
    NumVSites += Data->NumValueSites[VKI];

  ValueProfNode **Mem =
      (ValueProfNode **)calloc(NumVSites, sizeof(ValueProfNode *));
  if (!Mem)
    return 0;
  if (!COMPILER_RT_BOOL_CMPXCHG(&Data->Values, 0, Mem)) {
    free(Mem);
    return 0;
  }
  return 1;
}