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
struct TYPE_3__ {size_t text_num; int /*<<< orphan*/ * text_strings; int /*<<< orphan*/ * text_keys; } ;
typedef  TYPE_1__ LodePNGInfo ;

/* Variables and functions */
 int /*<<< orphan*/  lodepng_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void LodePNGText_cleanup(LodePNGInfo* info)
{
  size_t i;
  for(i = 0; i < info->text_num; i++)
  {
    string_cleanup(&info->text_keys[i]);
    string_cleanup(&info->text_strings[i]);
  }
  lodepng_free(info->text_keys);
  lodepng_free(info->text_strings);
}