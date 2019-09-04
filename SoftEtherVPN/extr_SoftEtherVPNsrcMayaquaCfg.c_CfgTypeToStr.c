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
typedef  int UINT ;

/* Variables and functions */
#define  ITEM_TYPE_BOOL 132 
#define  ITEM_TYPE_BYTE 131 
#define  ITEM_TYPE_INT 130 
#define  ITEM_TYPE_INT64 129 
#define  ITEM_TYPE_STRING 128 
 char* TAG_BOOL ; 
 char* TAG_BYTE ; 
 char* TAG_INT ; 
 char* TAG_INT64 ; 
 char* TAG_STRING ; 

char *CfgTypeToStr(UINT type)
{
	switch (type)
	{
	case ITEM_TYPE_INT:
		return TAG_INT;
	case ITEM_TYPE_INT64:
		return TAG_INT64;
	case ITEM_TYPE_BYTE:
		return TAG_BYTE;
	case ITEM_TYPE_STRING:
		return TAG_STRING;
	case ITEM_TYPE_BOOL:
		return TAG_BOOL;
	}
	return NULL;
}