#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  font_extra; } ;
typedef  int /*<<< orphan*/  PS_FontExtraRec ;
typedef  scalar_t__ FT_Face ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  TYPE_1__* CID_Face ;

/* Variables and functions */
 int /*<<< orphan*/  CID_Err_Ok ; 

__attribute__((used)) static FT_Error
  cid_ps_get_font_extra( FT_Face          face,
                        PS_FontExtraRec*  afont_extra )
  {
    *afont_extra = ((CID_Face)face)->font_extra;

    return CID_Err_Ok;
  }