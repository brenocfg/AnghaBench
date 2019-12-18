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

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 size_t JOB_ID_LEN ; 

int validateJobID(char *id, size_t len) {
    if (len != JOB_ID_LEN) return C_ERR;
    if (id[0] != 'D' ||
        id[1] != '-' ||
        id[10] != '-' ||
        id[35] != '-') return C_ERR;
    return C_OK;
}