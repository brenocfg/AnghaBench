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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  FSE_CTable ;

/* Variables and functions */
 int FSE_CTABLE_SIZE_U32 (unsigned int,unsigned int) ; 
 unsigned int FSE_TABLELOG_ABSOLUTE_MAX ; 
 scalar_t__ malloc (size_t) ; 

FSE_CTable* FSE_createCTable (unsigned maxSymbolValue, unsigned tableLog)
{
    size_t size;
    if (tableLog > FSE_TABLELOG_ABSOLUTE_MAX) tableLog = FSE_TABLELOG_ABSOLUTE_MAX;
    size = FSE_CTABLE_SIZE_U32 (tableLog, maxSymbolValue) * sizeof(U32);
    return (FSE_CTable*)malloc(size);
}