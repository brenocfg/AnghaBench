#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT8 ;
struct TYPE_4__ {int* key; } ;
struct TYPE_5__ {int* nb; } ;
struct TYPE_6__ {size_t key_size; int ediv; TYPE_1__ ltk; TYPE_2__ rand_nb; } ;

/* Variables and functions */
 size_t RAND_NB_LEN ; 
 size_t SEC_KEY_LEN ; 
 TYPE_3__ app_sec_env ; 
 int random () ; 

void app_ble_sec_gen_ltk(UINT8 key_size)
{
    // Counter
    UINT8 i;
    app_sec_env.key_size = key_size;

    // Randomly generate the LTK and the Random Number
    for (i = 0; i < RAND_NB_LEN; i++) {
        app_sec_env.rand_nb.nb[i] = random() % 256;
    }

    // Randomly generate the end of the LTK
    for (i = 0; i < SEC_KEY_LEN; i++) {
        app_sec_env.ltk.key[i] = (((key_size) < (16 - i)) ? 0 : random() % 256);
    }

    // Randomly generate the EDIV
    app_sec_env.ediv = random() % 65536;
}