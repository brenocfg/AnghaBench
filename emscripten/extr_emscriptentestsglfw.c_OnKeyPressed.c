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
 int GLFW_KEY_ENTER ; 
 int GLFW_PRESS ; 
 int GLFW_RELEASE ; 
 char* GetKeyName (int) ; 
 int /*<<< orphan*/  PullInfo () ; 
 int /*<<< orphan*/  printf (char*,char const*,int) ; 

void OnKeyPressed( int key, int action ){
  const char* key_name = GetKeyName(key);
  if(key_name == 0)
    return;
  if(action == GLFW_PRESS)
    printf("'%s' (%i) key is pressed\n", key_name, key);
  if(action == GLFW_RELEASE)
    printf("'%s' (%i) key is released\n", key_name, key);
  if(action == GLFW_RELEASE && key == GLFW_KEY_ENTER)
    PullInfo();
}