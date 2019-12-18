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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SSA_2_HB_TIME (int,int,int,int) ; 
 int sscanf (char*,char*,int*,int*,int*,int*,int*,int*,int*,int*) ; 

__attribute__((used)) static int parse_timing( char *line, int64_t *start, int64_t *stop )
{
    /*
     * Parse Start and End fields for timing information
     */
    int start_hr, start_min, start_sec, start_centi;
    int   end_hr,   end_min,   end_sec,   end_centi;
    // SSA subtitles have an empty layer field (bare ',').  The scanf
    // format specifier "%*128[^,]" will not match on a bare ','.  There
    // must be at least one non ',' character in the match.  So the format
    // specifier is placed directly next to the ':' so that the next
    // expected ' ' after the ':' will be the character it matches on
    // when there is no layer field.
    int numPartsRead = sscanf(line, "Dialogue:%*128[^,],"
        "%d:%d:%d.%d,"  // Start
        "%d:%d:%d.%d,", // End
        &start_hr, &start_min, &start_sec, &start_centi,
          &end_hr,   &end_min,   &end_sec,   &end_centi );
    if ( numPartsRead != 8 )
        return 1;

    *start = SSA_2_HB_TIME(start_hr, start_min, start_sec, start_centi);
    *stop  = SSA_2_HB_TIME(  end_hr,   end_min,   end_sec,   end_centi);

    return 0;
}