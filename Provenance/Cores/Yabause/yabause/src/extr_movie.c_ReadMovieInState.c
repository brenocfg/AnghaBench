#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct MovieBufferStruct {char size; char* data; } ;
struct TYPE_2__ {scalar_t__ Status; scalar_t__ ReadOnly; int /*<<< orphan*/  fp; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__ Movie ; 
 scalar_t__ Playback ; 
 scalar_t__ Recording ; 
 int /*<<< orphan*/  SEEK_SET ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (char) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ ) ; 

void ReadMovieInState(FILE* fp) {

	struct MovieBufferStruct tempbuffer;
	int fpos;
   size_t num_read = 0;

	//overwrite the main movie on disk if we are recording or read+write playback
	if(Movie.Status == Recording || (Movie.Status == Playback && Movie.ReadOnly == 0)) {

		fpos=ftell(fp);//where we are in the savestate
      num_read = fread(&tempbuffer.size, 4, 1, fp);//size
		if ((tempbuffer.data = (char *)malloc(tempbuffer.size)) == NULL)
		{
			return;
		}
      num_read = fread(tempbuffer.data, 1, tempbuffer.size, fp);//movie
		fseek(fp, fpos, SEEK_SET);//reset savestate position

		rewind(Movie.fp);
		fwrite(tempbuffer.data, 1, tempbuffer.size, Movie.fp);
		rewind(Movie.fp);
	}
}