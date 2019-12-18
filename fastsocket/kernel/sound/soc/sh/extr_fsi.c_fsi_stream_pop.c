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
struct fsi_priv {scalar_t__ periods; scalar_t__ byte_offset; scalar_t__ period_len; scalar_t__ buffer_len; int /*<<< orphan*/ * substream; } ;

/* Variables and functions */

__attribute__((used)) static void fsi_stream_pop(struct fsi_priv *fsi)
{
	fsi->substream		= NULL;
	fsi->buffer_len		= 0;
	fsi->period_len		= 0;
	fsi->byte_offset	= 0;
	fsi->periods		= 0;
}