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
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 unsigned int ARM_PMAP_MAX_OFFSET_DEFAULT ; 
 unsigned int ARM_PMAP_MAX_OFFSET_DEVICE ; 
 unsigned int ARM_PMAP_MAX_OFFSET_MAX ; 
 unsigned int ARM_PMAP_MAX_OFFSET_MIN ; 
#define  MACHINE_MAX_OFFSET_DEFAULT 131 
#define  MACHINE_MAX_OFFSET_DEVICE 130 
#define  MACHINE_MAX_OFFSET_MAX 129 
#define  MACHINE_MAX_OFFSET_MIN 128 
 int /*<<< orphan*/  panic (char*,unsigned int) ; 
 int /*<<< orphan*/  pmap_max_offset (int /*<<< orphan*/ ,unsigned int) ; 

vm_map_offset_t
ml_get_max_offset(
	boolean_t	is64,
	unsigned int option)
{
	unsigned int	pmap_max_offset_option = 0;

	switch (option) {
	case MACHINE_MAX_OFFSET_DEFAULT:
		pmap_max_offset_option = ARM_PMAP_MAX_OFFSET_DEFAULT;
                break;
        case MACHINE_MAX_OFFSET_MIN:
		pmap_max_offset_option =  ARM_PMAP_MAX_OFFSET_MIN;
                break;
        case MACHINE_MAX_OFFSET_MAX:
		pmap_max_offset_option = ARM_PMAP_MAX_OFFSET_MAX;
                break;
        case MACHINE_MAX_OFFSET_DEVICE:
		pmap_max_offset_option = ARM_PMAP_MAX_OFFSET_DEVICE;
                break;
        default:
		panic("ml_get_max_offset(): Illegal option 0x%x\n", option);
                break;
        }
	return pmap_max_offset(is64, pmap_max_offset_option);
}