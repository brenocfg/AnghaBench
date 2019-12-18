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
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;

/* Variables and functions */
 int /*<<< orphan*/  ff_img_tags ; 
 int str2id (int /*<<< orphan*/ ,char const*) ; 

enum AVCodecID ff_guess_image2_codec(const char *filename)
{
    return str2id(ff_img_tags, filename);
}