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
typedef  int /*<<< orphan*/  pixels ;
struct TYPE_3__ {int member_0; int member_1; unsigned char* member_2; } ;
typedef  TYPE_1__ GLFWimage ;
typedef  int /*<<< orphan*/  Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  _glfwCreateCursor (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Cursor createNULLCursor(void)
{
    unsigned char pixels[16 * 16 * 4];
    GLFWimage image = { 16, 16, pixels };

    memset(pixels, 0, sizeof(pixels));

    return _glfwCreateCursor(&image, 0, 0);
}