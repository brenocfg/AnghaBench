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
 int emscripten_run_script_int (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int snprintf (char*,int,char const*,int /*<<< orphan*/ *) ; 

int is_surface_freed(SDL_Surface *surface)
{
    const char *template = "!SDL.surfaces[%d]";
    int length = snprintf(NULL, 0, template, surface) + 1;
    char *script = malloc(length * sizeof(char));
    snprintf(script, length, template, surface);
    int is_freed = emscripten_run_script_int(script);
    free(script);
    return is_freed;
}