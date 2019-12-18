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
struct zr36060 {int mode; int /*<<< orphan*/  name; } ;
struct videocodec {scalar_t__ data; } ;

/* Variables and functions */
 int CODEC_DO_COMPRESSION ; 
 int CODEC_DO_EXPANSION ; 
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zr36060_init (struct zr36060*) ; 

__attribute__((used)) static int
zr36060_set_mode (struct videocodec *codec,
		  int                mode)
{
	struct zr36060 *ptr = (struct zr36060 *) codec->data;

	dprintk(2, "%s: set_mode %d call\n", ptr->name, mode);

	if ((mode != CODEC_DO_EXPANSION) && (mode != CODEC_DO_COMPRESSION))
		return -EINVAL;

	ptr->mode = mode;
	zr36060_init(ptr);

	return 0;
}