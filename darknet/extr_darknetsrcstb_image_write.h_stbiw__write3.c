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
struct TYPE_3__ {int /*<<< orphan*/  context; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,unsigned char*,int) ;} ;
typedef  TYPE_1__ stbi__write_context ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static void stbiw__write3(stbi__write_context *s, unsigned char a, unsigned char b, unsigned char c)
{
   unsigned char arr[3];
   arr[0] = a, arr[1] = b, arr[2] = c;
   s->func(s->context, arr, 3);
}