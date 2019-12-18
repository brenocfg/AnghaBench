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
struct saa7134_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  saa7134_hw_enable2 (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_tvaudio_init2 (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_video_init2 (struct saa7134_dev*) ; 

__attribute__((used)) static int saa7134_hwinit2(struct saa7134_dev *dev)
{

	dprintk("hwinit2\n");

	saa7134_video_init2(dev);
	saa7134_tvaudio_init2(dev);

	saa7134_hw_enable2(dev);

	return 0;
}