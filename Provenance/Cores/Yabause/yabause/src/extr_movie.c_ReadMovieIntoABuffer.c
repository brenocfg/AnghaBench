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
struct MovieBufferStruct {int size; char* data; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* ftell (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 

struct MovieBufferStruct ReadMovieIntoABuffer(FILE* fp) {

	int fpos;
	struct MovieBufferStruct tempbuffer;
   size_t num_read = 0;

	fpos = ftell(fp);//save current pos

	fseek (fp,0,SEEK_END);
	tempbuffer.size=ftell(fp);  //get size
	rewind(fp);

	tempbuffer.data = (char*) malloc (sizeof(char)*tempbuffer.size);
   num_read = fread(tempbuffer.data, 1, tempbuffer.size, fp);

	fseek(fp, fpos, SEEK_SET); //reset back to correct pos
	return(tempbuffer);
}