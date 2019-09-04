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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  DC_PEN ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDCPenColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void win_set_rgb (HDC hdc,
                                uint32_t rgb)
{
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, RGB((rgb & 4) * 0x33,
                           (rgb & 2) * 0x66,
                           (rgb & 1) * 0xcc));
}