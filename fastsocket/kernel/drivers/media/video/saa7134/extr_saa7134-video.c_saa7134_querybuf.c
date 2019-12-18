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
struct v4l2_buffer {int dummy; } ;
struct saa7134_fh {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  saa7134_queue (struct saa7134_fh*) ; 
 int videobuf_querybuf (int /*<<< orphan*/ ,struct v4l2_buffer*) ; 

__attribute__((used)) static int saa7134_querybuf(struct file *file, void *priv,
					struct v4l2_buffer *b)
{
	struct saa7134_fh *fh = priv;
	return videobuf_querybuf(saa7134_queue(fh), b);
}