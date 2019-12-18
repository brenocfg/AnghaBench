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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  qint64 ;

/* Variables and functions */
 int /*<<< orphan*/  Com_DPrintf (char*,int) ; 
 int /*<<< orphan*/  LittleLong64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_RankAsciiDecode (unsigned char*,char const*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static uint64_t SV_RankDecodePlayerID( const char* string )
{
	unsigned char	buffer[9];
	int len;
	qint64	player_id;

	assert( string != NULL );
	
	len = strlen (string) ;
	Com_DPrintf( "SV_RankDecodePlayerID: string length %d\n",len );
	SV_RankAsciiDecode( buffer, string, len );
	player_id = LittleLong64(*(qint64*)buffer);
	return *(uint64_t*)&player_id;
}