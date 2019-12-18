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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int kctype_subtype_t ;

/* Variables and functions */
#define  KC_ST_CHAR 136 
#define  KC_ST_INT16 135 
#define  KC_ST_INT32 134 
#define  KC_ST_INT64 133 
#define  KC_ST_INT8 132 
#define  KC_ST_UINT16 131 
#define  KC_ST_UINT32 130 
#define  KC_ST_UINT64 129 
#define  KC_ST_UINT8 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
get_kctype_subtype_size(kctype_subtype_t type)
{
	switch (type) {
	case KC_ST_CHAR:
	case KC_ST_INT8:
	case KC_ST_UINT8:
		return sizeof(uint8_t);
		break;
	case KC_ST_INT16:
	case KC_ST_UINT16:
		return sizeof(uint16_t);
		break;
	case KC_ST_INT32:
	case KC_ST_UINT32:
		return sizeof(uint32_t);
		break;
	case KC_ST_INT64:
	case KC_ST_UINT64:
		return sizeof(uint64_t);
		break;

	default:
		assert(0);
		break;
	}
	return 0;
}