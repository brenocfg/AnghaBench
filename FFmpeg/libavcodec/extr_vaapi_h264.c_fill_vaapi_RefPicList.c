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
typedef  int /*<<< orphan*/  VAPictureH264 ;
struct TYPE_3__ {scalar_t__ reference; int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ H264Ref ;

/* Variables and functions */
 int /*<<< orphan*/  fill_vaapi_pic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  init_vaapi_pic (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fill_vaapi_RefPicList(VAPictureH264 RefPicList[32],
                                  const H264Ref *ref_list,
                                  unsigned int  ref_count)
{
    unsigned int i, n = 0;
    for (i = 0; i < ref_count; i++)
        if (ref_list[i].reference)
            fill_vaapi_pic(&RefPicList[n++], ref_list[i].parent,
                           ref_list[i].reference);

    for (; n < 32; n++)
        init_vaapi_pic(&RefPicList[n]);
}