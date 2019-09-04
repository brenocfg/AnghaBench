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
typedef  int /*<<< orphan*/  SDL_Surface ;

/* Variables and functions */
 char* IMG_GetError () ; 
 int /*<<< orphan*/ * IMG_Load (char const*) ; 
 int /*<<< orphan*/  SDL_FreeSurface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void loadImage(const char* fileName) {
  SDL_Surface *image = IMG_Load(fileName);
  if (!image) {
     printf("IMG_Load: %s\n", IMG_GetError());
     abort();
  }
  SDL_FreeSurface(image);
}