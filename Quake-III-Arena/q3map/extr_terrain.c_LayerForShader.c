#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* shader; } ;
typedef  TYPE_1__ shaderInfo_t ;

/* Variables and functions */
 int atoi (char*) ; 
 int strlen (char*) ; 

int LayerForShader( shaderInfo_t *shader ) {
	int i;
	int l;

	l = strlen( shader->shader );
	for( i = l - 1; i >= 0; i-- ) {
		if ( shader->shader[ i ] == '_' ) {
			return atoi( &shader->shader[ i + 1 ] );
			break;
		}
	}

	return 0;
}