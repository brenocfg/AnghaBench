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
struct TYPE_2__ {int /*<<< orphan*/  Rerecords; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__ Movie ; 
 int /*<<< orphan*/  SEEK_SET ; 
 size_t fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int headersize ; 

__attribute__((used)) static void ReadHeader(FILE* fp) {
   size_t num_read = 0;

	fseek(fp, 0, SEEK_SET);

	fseek(fp, 172, SEEK_SET);
   num_read = fread(&Movie.Rerecords, sizeof(Movie.Rerecords), 1, fp);

	fseek(fp, headersize, SEEK_SET);
}