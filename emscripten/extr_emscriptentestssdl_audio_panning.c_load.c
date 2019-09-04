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
struct stat {int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  SDL_RWops ;
typedef  int /*<<< orphan*/  Mix_Chunk ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * Mix_LoadWAV_RW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_FreeRW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SDL_RWFromConstMem (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fread (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int stat (char const*,struct stat*) ; 

Mix_Chunk*
load(const char* filename)
{
  struct stat info;
  int result = stat(filename, &info);
  char * bytes = malloc( info.st_size );
  FILE * f = fopen( filename, "rb" );
  fread( bytes, 1, info.st_size, f  );
  fclose(f);

  SDL_RWops * ops = SDL_RWFromConstMem(bytes, info.st_size);
  Mix_Chunk * chunk = Mix_LoadWAV_RW(ops, 0);
  SDL_FreeRW(ops);
  free(bytes);

  return chunk;
}