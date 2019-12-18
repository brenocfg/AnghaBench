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
struct seq_file {int dummy; } ;
struct individual_sensor {int token; } ;
typedef  int /*<<< orphan*/  power_source ;
typedef  int /*<<< orphan*/  lid_status ;
typedef  int /*<<< orphan*/  key_switch ;
typedef  int /*<<< orphan*/  ibm_drconnector ;
typedef  int /*<<< orphan*/  epow_sensor ;
typedef  int /*<<< orphan*/  enclosure_switch ;
typedef  int /*<<< orphan*/  battery_remaining ;
typedef  int /*<<< orphan*/  battery_cyclestate ;
typedef  int /*<<< orphan*/  battery_charging ;

/* Variables and functions */
#define  BATTERY_CHARGING 143 
#define  BATTERY_CYCLESTATE 142 
#define  BATTERY_PERCENTAGE 141 
#define  BATTERY_REMAINING 140 
#define  BATTERY_VOLTAGE 139 
#define  ENCLOSURE_SWITCH 138 
#define  EPOW_SENSOR 137 
#define  IBM_DRCONNECTOR 136 
#define  IBM_FANRPM 135 
#define  IBM_POWERSUPPLY 134 
#define  IBM_SURVEILLANCE 133 
#define  IBM_VOLTAGE 132 
#define  KEY_SWITCH 131 
#define  LID_STATUS 130 
#define  POWER_SOURCE 129 
#define  THERMAL_SENSOR 128 
 int /*<<< orphan*/  cel_to_fahr (int) ; 
 int /*<<< orphan*/  get_location_code (struct seq_file*,struct individual_sensor*,char const*) ; 
 int ppc_rtas_process_error (int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void ppc_rtas_process_sensor(struct seq_file *m,
	struct individual_sensor *s, int state, int error, const char *loc)
{
	/* Defined return vales */
	const char * key_switch[]        = { "Off\t", "Normal\t", "Secure\t", 
						"Maintenance" };
	const char * enclosure_switch[]  = { "Closed", "Open" };
	const char * lid_status[]        = { " ", "Open", "Closed" };
	const char * power_source[]      = { "AC\t", "Battery", 
		  				"AC & Battery" };
	const char * battery_remaining[] = { "Very Low", "Low", "Mid", "High" };
	const char * epow_sensor[]       = { 
		"EPOW Reset", "Cooling warning", "Power warning",
		"System shutdown", "System halt", "EPOW main enclosure",
		"EPOW power off" };
	const char * battery_cyclestate[]  = { "None", "In progress", 
						"Requested" };
	const char * battery_charging[]    = { "Charging", "Discharching", 
						"No current flow" };
	const char * ibm_drconnector[]     = { "Empty", "Present", "Unusable", 
						"Exchange" };

	int have_strings = 0;
	int num_states = 0;
	int temperature = 0;
	int unknown = 0;

	/* What kind of sensor do we have here? */
	
	switch (s->token) {
		case KEY_SWITCH:
			seq_printf(m, "Key switch:\t");
			num_states = sizeof(key_switch) / sizeof(char *);
			if (state < num_states) {
				seq_printf(m, "%s\t", key_switch[state]);
				have_strings = 1;
			}
			break;
		case ENCLOSURE_SWITCH:
			seq_printf(m, "Enclosure switch:\t");
			num_states = sizeof(enclosure_switch) / sizeof(char *);
			if (state < num_states) {
				seq_printf(m, "%s\t", 
						enclosure_switch[state]);
				have_strings = 1;
			}
			break;
		case THERMAL_SENSOR:
			seq_printf(m, "Temp. (C/F):\t");
			temperature = 1;
			break;
		case LID_STATUS:
			seq_printf(m, "Lid status:\t");
			num_states = sizeof(lid_status) / sizeof(char *);
			if (state < num_states) {
				seq_printf(m, "%s\t", lid_status[state]);
				have_strings = 1;
			}
			break;
		case POWER_SOURCE:
			seq_printf(m, "Power source:\t");
			num_states = sizeof(power_source) / sizeof(char *);
			if (state < num_states) {
				seq_printf(m, "%s\t", 
						power_source[state]);
				have_strings = 1;
			}
			break;
		case BATTERY_VOLTAGE:
			seq_printf(m, "Battery voltage:\t");
			break;
		case BATTERY_REMAINING:
			seq_printf(m, "Battery remaining:\t");
			num_states = sizeof(battery_remaining) / sizeof(char *);
			if (state < num_states)
			{
				seq_printf(m, "%s\t", 
						battery_remaining[state]);
				have_strings = 1;
			}
			break;
		case BATTERY_PERCENTAGE:
			seq_printf(m, "Battery percentage:\t");
			break;
		case EPOW_SENSOR:
			seq_printf(m, "EPOW Sensor:\t");
			num_states = sizeof(epow_sensor) / sizeof(char *);
			if (state < num_states) {
				seq_printf(m, "%s\t", epow_sensor[state]);
				have_strings = 1;
			}
			break;
		case BATTERY_CYCLESTATE:
			seq_printf(m, "Battery cyclestate:\t");
			num_states = sizeof(battery_cyclestate) / 
				     	sizeof(char *);
			if (state < num_states) {
				seq_printf(m, "%s\t", 
						battery_cyclestate[state]);
				have_strings = 1;
			}
			break;
		case BATTERY_CHARGING:
			seq_printf(m, "Battery Charging:\t");
			num_states = sizeof(battery_charging) / sizeof(char *);
			if (state < num_states) {
				seq_printf(m, "%s\t", 
						battery_charging[state]);
				have_strings = 1;
			}
			break;
		case IBM_SURVEILLANCE:
			seq_printf(m, "Surveillance:\t");
			break;
		case IBM_FANRPM:
			seq_printf(m, "Fan (rpm):\t");
			break;
		case IBM_VOLTAGE:
			seq_printf(m, "Voltage (mv):\t");
			break;
		case IBM_DRCONNECTOR:
			seq_printf(m, "DR connector:\t");
			num_states = sizeof(ibm_drconnector) / sizeof(char *);
			if (state < num_states) {
				seq_printf(m, "%s\t", 
						ibm_drconnector[state]);
				have_strings = 1;
			}
			break;
		case IBM_POWERSUPPLY:
			seq_printf(m, "Powersupply:\t");
			break;
		default:
			seq_printf(m,  "Unknown sensor (type %d), ignoring it\n",
					s->token);
			unknown = 1;
			have_strings = 1;
			break;
	}
	if (have_strings == 0) {
		if (temperature) {
			seq_printf(m, "%4d /%4d\t", state, cel_to_fahr(state));
		} else
			seq_printf(m, "%10d\t", state);
	}
	if (unknown == 0) {
		seq_printf(m, "%s\t", ppc_rtas_process_error(error));
		get_location_code(m, s, loc);
	}
}