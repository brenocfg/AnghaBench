__attribute__((used)) static void t6() {
    int a[2][3];
    int *p = a;
    *(p + 4) = 65;
    t6a(65, a);
}