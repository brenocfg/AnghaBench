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
struct TYPE_2__ {int Frames; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__ Movie ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int framelength ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int headersize ; 

__attribute__((used)) static int MovieGetSize(FILE* fp) {
	int size;
	int fpos;

	fpos = ftell(fp);//save current pos

	fseek (fp,0,SEEK_END);
	size=ftell(fp);

	Movie.Frames=(size-headersize)/ framelength;

	fseek(fp, fpos, SEEK_SET); //reset back to correct pos
	return(size);
}