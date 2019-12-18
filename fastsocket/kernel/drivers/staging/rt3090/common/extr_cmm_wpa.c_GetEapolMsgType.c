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
typedef  char* PSTRING ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */
 scalar_t__ EAPOL_GROUP_MSG_1 ; 
 scalar_t__ EAPOL_GROUP_MSG_2 ; 
 scalar_t__ EAPOL_PAIR_MSG_1 ; 
 scalar_t__ EAPOL_PAIR_MSG_2 ; 
 scalar_t__ EAPOL_PAIR_MSG_3 ; 
 scalar_t__ EAPOL_PAIR_MSG_4 ; 

PSTRING GetEapolMsgType(CHAR msg)
{
    if(msg == EAPOL_PAIR_MSG_1)
        return "Pairwise Message 1";
    else if(msg == EAPOL_PAIR_MSG_2)
        return "Pairwise Message 2";
	else if(msg == EAPOL_PAIR_MSG_3)
        return "Pairwise Message 3";
	else if(msg == EAPOL_PAIR_MSG_4)
        return "Pairwise Message 4";
	else if(msg == EAPOL_GROUP_MSG_1)
        return "Group Message 1";
	else if(msg == EAPOL_GROUP_MSG_2)
        return "Group Message 2";
    else
	return "Invalid Message";
}