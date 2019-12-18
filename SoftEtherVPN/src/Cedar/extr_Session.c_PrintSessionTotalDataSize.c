#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ TotalRecvSize; scalar_t__ TotalRecvSizeReal; scalar_t__ TotalSendSize; scalar_t__ TotalSendSizeReal; } ;
typedef  TYPE_1__ SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,float,float) ; 

void PrintSessionTotalDataSize(SESSION *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	Debug(
		"-- SESSION TOTAL PKT INFORMATION --\n\n"
		"      TotalSendSize: %I64u\n"
		"  TotalSendSizeReal: %I64u\n"
		"      TotalRecvSize: %I64u\n"
		"  TotalRecvSizeReal: %I64u\n"
		"   Compression Rate: %.2f%% (Send)\n"
		"                     %.2f%% (Recv)\n",
		s->TotalSendSize, s->TotalSendSizeReal,
		s->TotalRecvSize, s->TotalRecvSizeReal,
		(float)((double)s->TotalSendSizeReal / (double)s->TotalSendSize * 100.0f),
		(float)((double)s->TotalRecvSizeReal / (double)s->TotalRecvSize * 100.0f)
		);

}