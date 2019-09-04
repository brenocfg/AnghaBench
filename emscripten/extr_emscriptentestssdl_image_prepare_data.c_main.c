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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_SWSURFACE ; 
 int /*<<< orphan*/  SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_run_preload_plugins_data (char*,int,char*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  ready ; 
 int /*<<< orphan*/  screen ; 

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(600, 450, 32, SDL_SWSURFACE);

  printf("prepare..\n");

  #define SIZE 203164
  FILE *f = fopen("screenshot.not", "rb");
  char *buffer = malloc(SIZE);
  fread(buffer, SIZE, 1, f);
  fclose(f);

  emscripten_run_preload_plugins_data(buffer, SIZE, "jpg", (void*)25, ready, NULL);
  emscripten_run_preload_plugins_data(buffer, SIZE, "jpg", (void*)33, ready, NULL); // twice to see different filenames

  return 0;
}