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
 int DISCONNECT_LONG ; 
 int DISCONNECT_NONE ; 
 int DISCONNECT_TIME_TO_DATA ; 
#define  FORMAT_UNIT 137 
#define  READ_10 136 
#define  READ_6 135 
#define  SEARCH_EQUAL 134 
#define  SEARCH_HIGH 133 
#define  SEARCH_LOW 132 
#define  SEEK_10 131 
#define  SEEK_6 130 
#define  WRITE_10 129 
#define  WRITE_6 128 

__attribute__((used)) static int should_disconnect(unsigned char cmd)
{
	switch (cmd) {
	case READ_6:
	case WRITE_6:
	case SEEK_6:
	case READ_10:
	case WRITE_10:
	case SEEK_10:
		return DISCONNECT_TIME_TO_DATA;
	case FORMAT_UNIT:
	case SEARCH_HIGH:
	case SEARCH_LOW:
	case SEARCH_EQUAL:
		return DISCONNECT_LONG;
	default:
		return DISCONNECT_NONE;
	}
}