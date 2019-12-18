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
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ILookInStream ;

/* Variables and functions */
 int /*<<< orphan*/  LookInStream_Read2 (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_INPUT_EOF ; 

SRes LookInStream_Read(ILookInStream *stream, void *buf, size_t size)
{
   return LookInStream_Read2(stream, buf, size, SZ_ERROR_INPUT_EOF);
}