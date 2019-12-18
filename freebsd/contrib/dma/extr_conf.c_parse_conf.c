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
typedef  int /*<<< orphan*/  line ;
struct TYPE_2__ {char* smarthost; char* aliases; char* spooldir; char* authpath; char* certfile; char* mailname; char* masquerade_host; char* masquerade_user; int features; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DEFER ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  EQS ; 
 int /*<<< orphan*/  EX_CONFIG ; 
 int /*<<< orphan*/  EX_NOINPUT ; 
 int FULLBOUNCE ; 
 int INSECURE ; 
 int NULLCLIENT ; 
 int SECURETRANS ; 
 int STARTTLS ; 
 int TLS_OPP ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  chomp (char*) ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  errlog (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  errlogx (int /*<<< orphan*/ ,char*,char const*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 char* strrchr (char*,char) ; 
 char* strsep (char**,int /*<<< orphan*/ ) ; 

void
parse_conf(const char *config_path)
{
	char *word;
	char *data;
	FILE *conf;
	char line[2048];
	int lineno = 0;

	conf = fopen(config_path, "r");
	if (conf == NULL) {
		/* Don't treat a non-existing config file as error */
		if (errno == ENOENT)
			return;
		errlog(EX_NOINPUT, "can not open config `%s'", config_path);
		/* NOTREACHED */
	}

	while (!feof(conf)) {
		if (fgets(line, sizeof(line), conf) == NULL)
			break;
		lineno++;

		chomp(line);

		/* We hit a comment */
		if (strchr(line, '#'))
			*strchr(line, '#') = 0;

		data = line;
		word = strsep(&data, EQS);

		/* Ignore empty lines */
		if (word == NULL || *word == 0)
			continue;

		if (data != NULL && *data != 0)
			data = strdup(data);
		else
			data = NULL;

		if (strcmp(word, "SMARTHOST") == 0 && data != NULL)
			config.smarthost = data;
		else if (strcmp(word, "PORT") == 0 && data != NULL)
			config.port = atoi(data);
		else if (strcmp(word, "ALIASES") == 0 && data != NULL)
			config.aliases = data;
		else if (strcmp(word, "SPOOLDIR") == 0 && data != NULL)
			config.spooldir = data;
		else if (strcmp(word, "AUTHPATH") == 0 && data != NULL)
			config.authpath= data;
		else if (strcmp(word, "CERTFILE") == 0 && data != NULL)
			config.certfile = data;
		else if (strcmp(word, "MAILNAME") == 0 && data != NULL)
			config.mailname = data;
		else if (strcmp(word, "MASQUERADE") == 0 && data != NULL) {
			char *user = NULL, *host = NULL;
			if (strrchr(data, '@')) {
				host = strrchr(data, '@');
				*host = 0;
				host++;
				user = data;
			} else {
				host = data;
			}
			if (host && *host == 0)
				host = NULL;
                        if (user && *user == 0)
                                user = NULL;
			config.masquerade_host = host;
			config.masquerade_user = user;
		} else if (strcmp(word, "STARTTLS") == 0 && data == NULL)
			config.features |= STARTTLS;
		else if (strcmp(word, "OPPORTUNISTIC_TLS") == 0 && data == NULL)
			config.features |= TLS_OPP;
		else if (strcmp(word, "SECURETRANSFER") == 0 && data == NULL)
			config.features |= SECURETRANS;
		else if (strcmp(word, "DEFER") == 0 && data == NULL)
			config.features |= DEFER;
		else if (strcmp(word, "INSECURE") == 0 && data == NULL)
			config.features |= INSECURE;
		else if (strcmp(word, "FULLBOUNCE") == 0 && data == NULL)
			config.features |= FULLBOUNCE;
		else if (strcmp(word, "NULLCLIENT") == 0 && data == NULL)
			config.features |= NULLCLIENT;
		else {
			errlogx(EX_CONFIG, "syntax error in %s:%d", config_path, lineno);
			/* NOTREACHED */
		}
	}

	if ((config.features & NULLCLIENT) && config.smarthost == NULL) {
		errlogx(EX_CONFIG, "%s: NULLCLIENT requires SMARTHOST", config_path);
		/* NOTREACHED */
	}

	fclose(conf);
}