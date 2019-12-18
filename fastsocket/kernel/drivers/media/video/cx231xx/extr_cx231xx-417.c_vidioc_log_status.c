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
struct file {int dummy; } ;
struct cx231xx_fh {struct cx231xx* dev; } ;
struct cx231xx {char* name; int /*<<< orphan*/  mpeg_params; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  call_all (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  cx2341x_log_status (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dprintk (int,char*,char*) ; 
 int /*<<< orphan*/  log_status ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int vidioc_log_status(struct file *file, void *priv)
{
	struct cx231xx_fh  *fh  = priv;
	struct cx231xx *dev = fh->dev;
	char name[32 + 2];

	snprintf(name, sizeof(name), "%s/2", dev->name);
	dprintk(3,
		"%s/2: ============  START LOG STATUS  ============\n",
	       dev->name);
	call_all(dev, core, log_status);
	cx2341x_log_status(&dev->mpeg_params, name);
	dprintk(3,
		"%s/2: =============  END LOG STATUS  =============\n",
	       dev->name);
	return 0;
}