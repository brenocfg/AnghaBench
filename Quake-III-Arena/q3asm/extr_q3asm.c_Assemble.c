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
struct TYPE_2__ {int segmentBase; int imageUsed; } ;

/* Variables and functions */
 int /*<<< orphan*/  AssembleLine () ; 
 size_t BSSSEG ; 
 size_t DATASEG ; 
 int /*<<< orphan*/  DefaultExtension (char*,char*) ; 
 int /*<<< orphan*/  DefineSymbol (char*,int) ; 
 char* ExtractLine (char*) ; 
 size_t LITSEG ; 
 int /*<<< orphan*/  LoadFile (char*,void**) ; 
 int MAX_OS_PATH ; 
 int NUM_SEGMENTS ; 
 int /*<<< orphan*/  WriteMapFile () ; 
 int /*<<< orphan*/  WriteVmFile () ; 
 char** asmFileNames ; 
 char** asmFiles ; 
 int currentFileIndex ; 
 scalar_t__ currentFileLine ; 
 char* currentFileName ; 
 scalar_t__ instructionCount ; 
 int numAsmFiles ; 
 char* outputFilename ; 
 int passNumber ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* segment ; 
 scalar_t__ stackSize ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void Assemble( void ) {
	int		i;
	char	filename[MAX_OS_PATH];
	char		*ptr;

	printf( "outputFilename: %s\n", outputFilename );

	for ( i = 0 ; i < numAsmFiles ; i++ ) {
		strcpy( filename, asmFileNames[ i ] );
		DefaultExtension( filename, ".asm" );
		LoadFile( filename, (void **)&asmFiles[i] );
	}

	// assemble
	for ( passNumber = 0 ; passNumber < 2 ; passNumber++ ) {
		segment[LITSEG].segmentBase = segment[DATASEG].imageUsed;
		segment[BSSSEG].segmentBase = segment[LITSEG].segmentBase + segment[LITSEG].imageUsed;
		for ( i = 0 ; i < NUM_SEGMENTS ; i++ ) {
			segment[i].imageUsed = 0;
		}
		segment[DATASEG].imageUsed = 4;		// skip the 0 byte, so NULL pointers are fixed up properly
		instructionCount = 0;

		for ( i = 0 ; i < numAsmFiles ; i++ ) {
			currentFileIndex = i;
			currentFileName = asmFileNames[ i ];
			currentFileLine = 0;
			printf("pass %i: %s\n", passNumber, currentFileName );
			ptr = asmFiles[i];
			while ( ptr ) {
				ptr = ExtractLine( ptr );
				AssembleLine();
			}
		}

		// align all segment
		for ( i = 0 ; i < NUM_SEGMENTS ; i++ ) {
			segment[i].imageUsed = (segment[i].imageUsed + 3) & ~3;
		}
	}

	// reserve the stack in bss
	DefineSymbol( "_stackStart", segment[BSSSEG].imageUsed );
	segment[BSSSEG].imageUsed += stackSize;
	DefineSymbol( "_stackEnd", segment[BSSSEG].imageUsed );

	// write the image
	WriteVmFile();

	// write the map file even if there were errors
	WriteMapFile();
}