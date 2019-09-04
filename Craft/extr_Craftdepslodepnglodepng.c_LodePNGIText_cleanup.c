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
struct TYPE_3__ {size_t itext_num; int /*<<< orphan*/ * itext_strings; int /*<<< orphan*/ * itext_transkeys; int /*<<< orphan*/ * itext_langtags; int /*<<< orphan*/ * itext_keys; } ;
typedef  TYPE_1__ LodePNGInfo ;

/* Variables and functions */
 int /*<<< orphan*/  lodepng_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void LodePNGIText_cleanup(LodePNGInfo* info)
{
  size_t i;
  for(i = 0; i < info->itext_num; i++)
  {
    string_cleanup(&info->itext_keys[i]);
    string_cleanup(&info->itext_langtags[i]);
    string_cleanup(&info->itext_transkeys[i]);
    string_cleanup(&info->itext_strings[i]);
  }
  lodepng_free(info->itext_keys);
  lodepng_free(info->itext_langtags);
  lodepng_free(info->itext_transkeys);
  lodepng_free(info->itext_strings);
}