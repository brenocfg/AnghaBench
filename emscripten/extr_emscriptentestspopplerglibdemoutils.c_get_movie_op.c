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
typedef  char gchar ;
typedef  int PopplerActionMovieOperation ;

/* Variables and functions */
#define  POPPLER_ACTION_MOVIE_PAUSE 131 
#define  POPPLER_ACTION_MOVIE_PLAY 130 
#define  POPPLER_ACTION_MOVIE_RESUME 129 
#define  POPPLER_ACTION_MOVIE_STOP 128 

__attribute__((used)) static const gchar *
get_movie_op (PopplerActionMovieOperation op)
{
	switch (op) {
	case POPPLER_ACTION_MOVIE_PLAY:
		return "Play";
	case POPPLER_ACTION_MOVIE_PAUSE:
		return "Pause";
	case POPPLER_ACTION_MOVIE_RESUME:
		return "Resume";
	case POPPLER_ACTION_MOVIE_STOP:
		return "Stop";
	}
	return NULL;
}