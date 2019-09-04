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
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void 
transpose(GLfloat *m)
{
   GLfloat t[16] = {
      m[0], m[4], m[8],  m[12],
      m[1], m[5], m[9],  m[13],
      m[2], m[6], m[10], m[14],
      m[3], m[7], m[11], m[15]};

   memcpy(m, t, sizeof(t));
}