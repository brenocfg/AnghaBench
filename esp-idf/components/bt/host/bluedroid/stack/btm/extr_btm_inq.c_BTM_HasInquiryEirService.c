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
struct TYPE_3__ {scalar_t__ eir_complete_list; int /*<<< orphan*/  eir_uuid; } ;
typedef  TYPE_1__ tBTM_INQ_RESULTS ;
typedef  int /*<<< orphan*/  tBTM_EIR_SEARCH_RESULT ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_EIR_FOUND ; 
 int /*<<< orphan*/  BTM_EIR_NOT_FOUND ; 
 int /*<<< orphan*/  BTM_EIR_UNKNOWN ; 
 scalar_t__ BTM_HasEirService (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tBTM_EIR_SEARCH_RESULT BTM_HasInquiryEirService( tBTM_INQ_RESULTS *p_results, UINT16 uuid16 )
{
    if ( BTM_HasEirService( p_results->eir_uuid, uuid16 )) {
        return BTM_EIR_FOUND;
    } else if ( p_results->eir_complete_list ) {
        return BTM_EIR_NOT_FOUND;
    } else {
        return BTM_EIR_UNKNOWN;
    }
}