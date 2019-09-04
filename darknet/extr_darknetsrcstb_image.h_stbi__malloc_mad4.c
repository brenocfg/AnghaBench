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

/* Variables and functions */
 int /*<<< orphan*/  stbi__mad4sizes_valid (int,int,int,int,int) ; 
 void* stbi__malloc (int) ; 

__attribute__((used)) static void *stbi__malloc_mad4(int a, int b, int c, int d, int add)
{
   if (!stbi__mad4sizes_valid(a, b, c, d, add)) return NULL;
   return stbi__malloc(a*b*c*d + add);
}