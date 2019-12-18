#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wi ;
struct TYPE_4__ {int cbSize; int /*<<< orphan*/  rcClient; } ;
typedef  TYPE_1__ WINDOWINFO ;

/* Variables and functions */
 int /*<<< orphan*/  FrameRectMy ; 
 int /*<<< orphan*/  FrameWnd ; 
 int /*<<< orphan*/  GetWindowInfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void UpdateRect(void)
{
  WINDOWINFO wi;
  memset(&wi, 0, sizeof(wi));
  wi.cbSize = sizeof(wi);
  GetWindowInfo(FrameWnd, &wi);
  FrameRectMy = wi.rcClient;
}