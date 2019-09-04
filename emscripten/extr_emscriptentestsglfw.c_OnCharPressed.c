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
 int GLFW_PRESS ; 
 int GLFW_RELEASE ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

void OnCharPressed( int character, int action ){
  if(action == GLFW_PRESS)
    printf("'%c' (%i) char is pressed\n", character, character);
  if(action == GLFW_RELEASE)
    printf("'%c' (%i) char is released\n", character, character);
}