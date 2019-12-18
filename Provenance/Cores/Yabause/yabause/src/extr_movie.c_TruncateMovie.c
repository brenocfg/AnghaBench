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
struct MovieStruct {int dummy; } ;

/* Variables and functions */

void TruncateMovie(struct MovieStruct Movie) {

	//when we resume recording, shorten the movie so that there isn't 
	//potential garbage data at the end

/*//TODO
	struct MovieBufferStruct tempbuffer;
	fseek(Movie.fp,0,SEEK_SET);
	tempbuffer=ReadMovieIntoABuffer(Movie.fp);
	fclose(Movie.fp);

	//clear the file and write it again
	Movie.fp=fopen(Movie.filename,"wb");
	fwrite(tempbuffer.data,framelength,framecounter,Movie.fp);
	fclose(Movie.fp);

	Movie.fp=fopen(Movie.filename,"r+b");
*/
}