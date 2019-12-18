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
typedef  int uint16_t ;

/* Variables and functions */
#define  Action_failed 131 
#define  Invalid_command 130 
#define  Invalid_parameter 129 
#define  Unknown_command 128 

char *Errcode_to_String(uint16_t status) 
{
    char *Errstr = NULL;
    switch (status) {
        case Unknown_command:
            Errstr = "Unknown_command";
            break;
        case Invalid_command:
            Errstr = "Invalid_command";
            break;
        case Invalid_parameter:
            Errstr = "Invalid_parameter";
            break;
        case Action_failed:
            Errstr = "Action_failed";
            break;
        default:
            Errstr = "unknown_failed";
            break;
    }
    return Errstr;

}