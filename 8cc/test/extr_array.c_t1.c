__attribute__((used)) static void t1() {
    int a[2][3];
    int *p = a;
    *p = 1;
    expect(1, *p);
}