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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct saa7134_fh {int /*<<< orphan*/  dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int saa7134_s_std_internal (int /*<<< orphan*/ ,struct saa7134_fh*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int saa7134_s_std(struct file *file, void *priv, v4l2_std_id *id)
{
	struct saa7134_fh *fh = priv;

	return saa7134_s_std_internal(fh->dev, fh, id);
}