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
#define  CARD_DETECTED 130 
#define  CARD_LOADING 129 
#define  CARD_RUNNING 128 

__attribute__((used)) static char *
cardstate2str(unsigned short cardstate)
{
	switch (cardstate) {
	case CARD_DETECTED:	return "detected";
	case CARD_LOADING:	return "loading";
	case CARD_RUNNING:	return "running";
	default:	        return "???";
	}
}