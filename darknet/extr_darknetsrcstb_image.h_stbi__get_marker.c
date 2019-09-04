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
typedef  int stbi_uc ;
struct TYPE_3__ {scalar_t__ marker; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ stbi__jpeg ;

/* Variables and functions */
 scalar_t__ STBI__MARKER_none ; 
 int stbi__get8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static stbi_uc stbi__get_marker(stbi__jpeg *j)
{
   stbi_uc x;
   if (j->marker != STBI__MARKER_none) { x = j->marker; j->marker = STBI__MARKER_none; return x; }
   x = stbi__get8(j->s);
   if (x != 0xff) return STBI__MARKER_none;
   while (x == 0xff)
      x = stbi__get8(j->s); // consume repeated 0xff fill bytes
   return x;
}