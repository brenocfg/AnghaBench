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
struct wchar_conv_struct {int /*<<< orphan*/  state; int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 size_t unicode_loop_reset (int /*<<< orphan*/ *,char**,size_t*) ; 

__attribute__((used)) static size_t wchar_to_loop_reset (iconv_t icd,
                                   char* * outbuf, size_t *outbytesleft)
{
  struct wchar_conv_struct * wcd = (struct wchar_conv_struct *) icd;
  size_t res = unicode_loop_reset(&wcd->parent,outbuf,outbytesleft);
  if (res == (size_t)(-1))
    return res;
  memset(&wcd->state,0,sizeof(mbstate_t));
  return 0;
}