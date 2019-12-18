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
 int djb2 (char const*) ; 
 int /*<<< orphan*/  printf (char*,int,char const*) ; 

int main(int argc, const char* argv[])
{
   int i;

   for (i = 1; i < argc; i++)
      printf( "0x%08xU: %s\n", djb2( argv[ i ] ), argv[ i ] );

   return 0;
}