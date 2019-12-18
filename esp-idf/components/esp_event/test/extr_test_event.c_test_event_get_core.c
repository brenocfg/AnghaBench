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
typedef  int BaseType_t ;

/* Variables and functions */
 int portNUM_PROCESSORS ; 
 int s_test_core_id ; 

__attribute__((used)) static BaseType_t test_event_get_core(void)
{
    static int calls = 0;

    if (portNUM_PROCESSORS > 1) {
        return (s_test_core_id + calls++) % portNUM_PROCESSORS;
    } else {
        return s_test_core_id;
    }
}